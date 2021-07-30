import pycurl
from threading import Thread
import sys

def init_curl():
    c = pycurl.Curl()
    c.setopt(pycurl.URL, sys.argv[1])
    c.setopt(pycurl.SSL_VERIFYPEER, 0)
    c.setopt(pycurl.SSL_VERIFYHOST, 0)
    c.setopt(pycurl.VERBOSE, 0)
    c.setopt(pycurl.COOKIEJAR, "cookie.txt")
    c.setopt(pycurl.COOKIEFILE, "")
    c.setopt(pycurl.FOLLOWLOCATION, 1)
    c.setopt(pycurl.WRITEFUNCTION, lambda x: None)
    return c

def run_curl():
    c = init_curl()
    while(True):
        c.perform()

for _ in range(10):
    Thread(target=run_curl).start()