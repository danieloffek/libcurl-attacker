import pycurl
from multiprocessing import Process
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

def run_curl_threads():
    for _ in range(4):
        Thread(target=run_curl).start()

def main():
    for _ in range(4):
        Process(target=run_curl_threads).start()

main()
