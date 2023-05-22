# ---------------------------------------------------------------------------------------------------
# REPEATED TIMER MODULE
# This module allows you to create a timer that can be set at a defined interval
# and will repeat itself until it's stopped.
#
# HOW TO
# 1. Define a procedure with the code that will be executed every time the timer expires.
# 2. Create the timer object to start it, example:
#    rt =  RepeatedTimer(seconds, procedure_to_call)
# 3. When the timer is no more useful, stop it:
#    rt.stop()
#
# CREDITS
# eraoul and MestreLion from StackOverflow
# https://stackoverflow.com/a/40965385
#
# --------------------------------------------------------------------------------------------------

import time
import threading


class RepeatedTimer(object):
    def __init__(self, interval, function, *args, **kwargs):
        self._timer = None
        self.interval = interval
        self.function = function
        self.args = args
        self.kwargs = kwargs
        self.is_running = False
        self.next_call = time.time()
        self.start()

    def _run(self):
        self.is_running = False
        self.start()
        self.function(*self.args, **self.kwargs)

    def start(self):
        if not self.is_running:
            self.next_call += self.interval
            self._timer = threading.Timer(self.next_call - time.time(), self._run)
            self._timer.start()
            self.is_running = True

    def stop(self):
        self._timer.cancel()
        self.is_running = False
