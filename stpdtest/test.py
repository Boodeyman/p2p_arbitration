# url = "https://coinmarketcap.com/ru/currencies/bitcoin/"
#
# url = url.split("/")
#
# print(url[-2])

from colorama import init, Fore, Back, Style
import time

init(autoreset=True)

for i in range(11):
    print(f"\r{Fore.GREEN}Прогресс: {i}/10", end='')
    time.sleep(1)

print(f"\n{Fore.BLUE}Готово!")

