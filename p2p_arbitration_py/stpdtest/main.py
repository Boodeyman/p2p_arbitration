import requests
from bs4 import BeautifulSoup
import time
from colorama import init, Fore, Back, Style

init(autoreset=True)


def get_data(url):
    start_time = time.time()
    headers = {
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/17.4 Safari/605.1.15"
    }
    req = requests.get(url, headers)
    with open('p2p_data', 'w') as file:
        file.write(req.text)
    with open('p2p_data') as file:
        src = file.read()

    soup = BeautifulSoup(src, "lxml")
    trs = soup.find_all("tr", style="cursor:pointer")

    coin_urls = []
    for tr in trs:
        coin_url = "https://coinmarketcap.com" + tr.find("a").get("href")
        coin_urls.append(coin_url)
        print(coin_url)

    coin_prices = [""] * 5  # Создаем список из 5 пустых строк для хранения цен

    while True:
        for i, coin_url in enumerate(coin_urls[0:5]):
            req = requests.get(coin_url, headers)
            coin_name = coin_url.split("/")[-2]

            with open(f"data/{coin_name}.html", "w") as file:
                file.write(req.text)
            with open(f"data/{coin_name}.html") as file:
                src = file.read()

            soup = BeautifulSoup(src, "lxml")
            coin_price = soup.find("span", class_="sc-f70bb44c-0 jxpCgO base-text").text

            coin_prices[
                i] = f"{Fore.GREEN}{coin_name}{Fore.RESET}: {Fore.RED}{coin_price}{Fore.RESET}"  # Обновляем цену в списке

        # Выводим все 5 цен на одной строке
        print(f"\rCoin_prices: {' '.join(coin_prices)}", end="")
        time.sleep(5)


get_data("https://coinmarketcap.com/")
