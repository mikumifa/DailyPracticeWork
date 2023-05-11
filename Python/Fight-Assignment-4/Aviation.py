from Flight import *
from Airport import *


class Aviation:
    def __init__(self):
        self._allAirports = {}
        self._allFlights = {}
        self._allCountries = {}

    def getAllAirports(self):
        return self._allAirports

    def getAllFlights(self):
        return self._allFlights

    def getAllCountries(self):
        return self._allCountries

    def setAllAirports(self, airports):
        self._allAirports = airports

    def setAllFlights(self, flights):
        self._allFlights = flights

    def setAllCountries(self, countries):
        self._allCountries = countries

    def loadData(self, airportFile, flightFile, countriesFile):
        try:
            self.__init__()
            cFile = open(countriesFile, "r")
            for line in cFile.readlines():
                parts = [v.strip(" \t\n") for v in line.split(',')]
                self._allCountries[parts[0]] = parts[1]
            aFile = open(airportFile, "r")
            for line in aFile.readlines():
                parts = [v.strip(" \t\n") for v in line.split(',')]
                airport = Airport(parts[0], parts[2], parts[1], self._allCountries[parts[1]])
                self._allAirports[parts[0]] = airport
            fFile = open(flightFile, "r")
            for line in fFile.readlines():
                parts = [v.strip(" \t\n") for v in line.split(',')]
                flight = Flight(parts[0], self._allAirports[parts[1]], self._allAirports[parts[2]])
                if parts[1] not in self._allFlights.keys():
                    self._allFlights[parts[1]] = [flight]
                else:
                    self._allFlights[parts[1]].append(flight)
        except FileNotFoundError:
            return False
        return True

    def getAirportByCode(self, code):
        return self._allAirports[code]

    def findAllCityFlights(self, city):
        flights = []
        for flightList in self._allFlights.values():
            for flight in flightList:
                if flight.getOrigin().getCity() == city or flight.getDestination().getCity() == city:
                    flights.append(flight)
        return flights

    def findFlightByNo(self, flightNo):
        for flightList in self._allFlights.values():
            for flight in flightList:
                if flight.getFlightNumber() == flightNo:
                    return flight
        return -1

    def findAllCountryFlights(self, country):
        flights = []
        for flightList in self._allFlights.values():
            for flight in flightList:
                if flight.getOrigin().getCountry() == country or flight.getDestination().getCountry() == country:
                    flights.append(flight)
        return flights

    def findFlightBetween(self, origAirport, destAirport):
        for flightList in self._allFlights.values():
            for flight in flightList:
                if flight.getOrigin() == origAirport and flight.getDestination() == destAirport:
                    return "Direct Flight({}): {} to {}".format(flight.getFlightNumber(), origAirport.getCode(),
                                                                destAirport.getCode())
        connectingAirports = set()
        for flightList in self._allFlights.values():
            for flight in flightList:
                if flight.getOrigin() == origAirport:
                    for secondFlightList in self._allFlights.values():
                        for secondFlight in secondFlightList:
                            if secondFlight.getDestination() == destAirport and secondFlight.getOrigin() != origAirport:
                                connectingAirports.add(secondFlight.getOrigin().getCode())
        if connectingAirports:
            return connectingAirports
        else:
            return -1

    def findReturnFlight(self, firstFlight):
        for flightList in self._allFlights.values():
            for flight in flightList:
                if flight.getOrigin() == firstFlight.getDestination() and flight.getDestination() == firstFlight.getOrigin():
                    return flight
        return -1

    def findFlightsAcross(self, ocean):
        flights = set()
        greenZone = {"South America", "North America"}
        redZone = {"Asia", "Australia"}
        blueZone = {"Europe", "Africa"}
        if ocean == "Pacific":
            for flightList in self._allFlights.values():
                for flight in flightList:
                    originCountry = flight.getOrigin().getCountry()
                    destCountry = flight.getDestination().getCountry()
                    if self._allCountries[originCountry] in greenZone and self._allCountries[destCountry] in redZone or self._allCountries[destCountry] in greenZone and self._allCountries[originCountry] in redZone:
                        flights.add(flight.getFlightNumber())
            return flights if flights else -1
        elif ocean == "Atlantic":
            for flightList in self._allFlights.values():
                for flight in flightList:
                    originCountry = flight.getOrigin().getCountry()
                    destCountry = flight.getDestination().getCountry()
                    if self._allCountries[originCountry] in greenZone and self._allCountries[destCountry] in blueZone or self._allCountries[destCountry] in greenZone and self._allCountries[originCountry] in blueZone:
                        flights.add(flight.getFlightNumber())
            return flights if flights else -1
        else:
            return -1
