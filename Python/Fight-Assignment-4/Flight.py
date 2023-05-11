from Airport import *
import re


class Flight:
    def __init__(self, flightNo, origAirport, destAirport):
        if not isinstance(origAirport, Airport) or not isinstance(destAirport, Airport):
            raise TypeError("The origin and destination must be Airport objects")
        if not isinstance(flightNo, str) or re.match('[a-zA-Z]{3}[0-9]{3}$', flightNo) is None:
            raise TypeError("The flight number format is incorrect")
        self._flightNo = flightNo
        self._origin = origAirport
        self._destination = destAirport

    def __repr__(self):
        return f'Flight({self._flightNo}): {self._origin.getCity()} -> {self._destination.getCity()} {"[domestic]" if self.isDomesticFlight() else "[international]"}'

    def __eq__(self, other):
        return self._origin == other.getOrigin() and self._destination == other.getDestination()

    def getFlightNumber(self):
        return self._flightNo

    def getDestination(self):
        return self._destination

    def getOrigin(self):
        return self._origin

    def isDomesticFlight(self) -> bool:
        return self._origin.getCountry() == self._destination.getCountry()

    def setOrigin(self, origin):
        self._origin = origin
        return

    def setDestination(self, destination):
        self._destination = destination
        return

    def getOriginAirport(self):
        return self._origin
