import requests
from bs4 import BeautifulSoup


def get_data(url):
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

    for coin_url in coin_urls[0:5]:
        req = requests.get(coin_url, headers)
        coin_name = coin_url.split("/")[-2]

        with open(f"data/{coin_name}.html", "w") as file:
            file.write(req.text)
        with open(f"data/{coin_name}.html") as file:
            src = file.read()

        soup = BeautifulSoup(src, "lxml")
        coin_price = soup.find("span", class_="sc-f70bb44c-0 jxpCgO base-text").text
        print(coin_price)
        # coin_data = soup.find_all("div", class_="sc-500f568e-0 ejtlWy")
        # rating_element = soup.find('div', {'el': 'sc-f70bb44c-0 jxpCgO base-text'})
        # print(coin_data)
        # print(rating_element)


get_data("https://coinmarketcap.com/")
