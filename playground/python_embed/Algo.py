#!/usr/bin/python

#our C++ application will provide AlgoAPI for Algo Place Order Cancel Order and so on

import AlgoAPI

market_tick_count = 0

def Init():
	market_tick_count = 0
	pass

def Stop():
	pass

def OnData(market_data):
	global market_tick_count
	market_tick_count = market_tick_count + 1
	print "Python onData", market_data , market_tick_count
	if (market_tick_count%3 == 0):
		print "Python will Call C++ place Order"
		AlgoAPI.PlaceOrder(market_tick_count)
		

def OnOrder(order):
	print (order)

def OnTrade(trade):
	print (trade)

def OnDisconnect():
	print "CTP disconnect"

