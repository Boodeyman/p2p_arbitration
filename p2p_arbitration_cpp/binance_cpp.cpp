#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct MemoryStruct {
    char* memory;
    size_t size;
};

size_t WriteMemoryCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t realsize = size * nmemb;
    struct MemoryStruct* mem = (struct MemoryStruct*)userp;

    char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
    if (ptr == NULL) {
        cout << "Not enough memory (realloc returned NULL)" << endl;
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

json get_crypto(const string& crypto = "BTCUSDT") {
    MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);  // will be grown as needed by the realloc above
    chunk.size = 0;                   // no data at this point

    CURL* curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        string url = "https://www.binance.com/bapi/asset/v2/public/asset-service/product/get-product-by-symbol?symbol=" + crypto;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
            free(chunk.memory);
            json error_data;
            error_data["name"] = crypto;
            error_data["current"] = "Error";
            error_data["change"] = "Error";
            return error_data;
        }
        curl_easy_cleanup(curl);
    }

    json data = json::parse(chunk.memory);
    free(chunk.memory);

    if (!data["success"].get<bool>()) {
        json error_data;
        error_data["name"] = crypto;
        error_data["current"] = "Unavailable";
        error_data["change"] = "Unavailable";
        return error_data;
    }

    double current_price = stod(data["data"]["c"].get<string>());
    double opening_price = stod(data["data"]["o"].get<string>());
    double change = round((current_price - opening_price) / opening_price * 10000) / 100;

    json crypto_data;
    crypto_data["name"] = data["data"]["an"].get<string>();
    crypto_data["current"] = to_string(current_price) + "$";
    crypto_data["change"] = (change >= 0 ? "+" : "") + to_string(change) + "%";
    return crypto_data;
}

vector<json> display_cryptos(const vector<string>& cryptos) {
    vector<json> results;
    for (const auto& crypto : cryptos) {
        results.push_back(get_crypto(crypto));
    }
    return results;
}

int main() {
    vector<string> cryptos = {"BTCUSDT", "ETHUSDT", "BNBUSDT", "XRPUSDT", "ADAUSDT"};

    while (true) {
        vector<json> crypto_data = display_cryptos(cryptos);
        cout << "\r"; // Reset line
        for (const auto& data : crypto_data) {
            cout << data["name"].get<string>() << ": " << data["current"].get<string>() << ", Change: " << data["change"].get<string>() << " | ";
        }
        cout << flush; // Ensure output is displayed
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}
