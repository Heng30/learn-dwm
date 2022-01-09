#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import requests
import json

dataList = []

headers = {
    "Accept":
    "text/html,application/xhtml+xml,application/xml;",
    "Accept-Encoding":
    "gzip",
    "Accept-Language":
    "zh-CN,zh;q=0.8",
    "Referer":
    "http://www.example.com/",
    "User-Agent":
    "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) \
                             Chrome/42.0.2311.90 Safari/537.36"
}


def coinPrice(coins):
    for coin in coins:
        url = 'https://api.alternative.me/v2/ticker/' + coin["name"] + '/'
        s = requests.Session()
        s.headers.update(headers)
        try:
            r = s.get(url)
        except Exception:
            continue

        data = json.loads(r.text)
        dataList.append(
            str(round(data['data'][coin["id"]]["quotes"]["USD"]["price"])))
        dataList.append(
            str(round(data['data'][coin["id"]]["quotes"]["USD"]["percentage_change_24h"])) + '%')


def fear():
    url = 'https://api.alternative.me/fng/?limit=2'
    s = requests.Session()
    s.headers.update(headers)
    try:
        r = s.get(url)
    except Exception:
        return

    data = json.loads(r.text)
    for j in data['data']:
        dataList.append(str(j['value']))


if __name__ == '__main__':
    coinPrice([{
        'name': 'bitcoin',
        'id': '1'
    }, {
        'name': 'ethereum',
        'id': '1027'
    }])

    fear()

    print(" ".join(dataList))
