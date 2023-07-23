from gunther import *

def test_socket():
    try:
        s4 = Socket4()
        s6 = Socket6()
    except:
        assert False, "Socket4/6 Failure"
