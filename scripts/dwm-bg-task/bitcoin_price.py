#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from bs4 import BeautifulSoup
from urllib.parse import quote
import requests
import string
import json
import sys

def output(msg):
    print(msg)


def parse():
    headers = {"Accept": "text/html,application/xhtml+xml,application/xml;",
               "Accept-Encoding": "gzip",
               "Accept-Language": "zh-CN,zh;q=0.8",
               "Referer": "http://www.example.com/",
               "User-Agent": "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) \
                             Chrome/42.0.2311.90 Safari/537.36"
               }
    url = 'https://www.bitcoinprice.com/'
    s = requests.Session()
    s.headers.update(headers)
    try:
        r = s.get(url)
    except Exception:
        output('0 0')
        exit()

    return BeautifulSoup(r.text, 'html.parser')


if __name__ == '__main__':
    prefix = '<script type="application/ld+json">'
    postfix = '</script>'

    soup = parse()
    array = soup.find_all('script', type='application/ld+json')
    for i in array:
        i = i.prettify()
        s = i.find(prefix)
        e = i.find(postfix)

        if s == -1 or e == -1:
            continue

        s += len(prefix)
        json_str = i[s:e]
        data = json.loads(json_str)

        info = ''
        for j in data['@graph']:
            if (j['name'] == 'BTC') or (j['name'] == 'ETH'):
                price = round(float(j['offers']['price']))
                info += str(price) + ' '

        if len(info) > 0:
            output(info)
            exit()

    output('0 0')
