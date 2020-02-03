#!/usr/bin/env python3
# -*- coding: utf-8 -*-

'''
查询城市天气预报
'''

import requests

res = requests.get("http://www.weather.com.cn/data/sk/101010100.html")
res.encoding = "utf-8"

result = res.json()
print("返回结果：%s" % result)
print("城市：%s" % result["weatherinfo"]["city"])
print("风向：%s" % result["weatherinfo"]["WD"])
print("温度：%s" % result["weatherinfo"]["temp"] + " 度")
print("风力：%s" % result["weatherinfo"]["WS"])
print("湿度：%s" % result["weatherinfo"]["SD"])