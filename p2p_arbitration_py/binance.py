from curl_cffi import requests
import time
from colorama import init, Fore, Style

init(autoreset=True)


def get_crypto(crypto='BTCUSDT'):
    try:
        url = f"https://www.binance.com/bapi/asset/v2/public/asset-service/product/get-product-by-symbol?symbol={crypto}"
        response = requests.get(url)
        data = response.json()

        if data['success']:  # Проверка успешности запроса
            current_price = float(data['data']['c'])
            opening_price = float(data['data']['o'])
            current = round(current_price, 2)
            change = round((current_price - opening_price) / opening_price * 100, 2)
            change = f"+{change}%" if change > 0 else f"{change}%"
            fullname = data['data']['an']
            return {
                'name': fullname,
                'current': f"{current}$",
                'change': change
            }
        else:
            # Обработка неудачного запроса, возможно, запись сообщения об ошибке
            return {
                'name': crypto,
                'current': 'Unavailable',
                'change': 'Unavailable'
            }
    except requests.RequestException as e:
        return {
            'name': crypto,
            'current': 'Error',
            'change': 'Error'
        }


def display_cryptos(cryptos):
    results = []
    for crypto in cryptos:
        result = get_crypto(crypto)
        results.append(result)
    return results


cryptos = ['BTCUSDT', 'ETHUSDT', 'BNBUSDT', 'XRPUSDT', 'ADAUSDT']

while True:
    crypto_data = display_cryptos(cryptos)
    output_lines = []
    for data in crypto_data:
        line = f"{Fore.GREEN}{data['name']}{Fore.RESET}: {Fore.RED}{data['current']}, Change: {data['change']}{Fore.RESET}"
        output_lines.append(line)

    # Вывод всех данных на одной строке
    print("\r" + ' | '.join(output_lines), end="")
    time.sleep(1)
