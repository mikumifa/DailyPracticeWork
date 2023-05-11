class Airport:
    def __init__(self, code, city, country, continent):
        self._code = code
        self._city = city
        self._country = country
        self._continent = continent

    def __repr__(self):
        return f'{self._code}({self._city}, {self._country})'

    def getCode(self):
        return self._code

    def getCountry(self):
        return self._country

    def getContinent(self):
        return self._continent

    def setCode(self, code):
        self._code = code
        return

    def setCountry(self, country):
        self._country = country
        return

    def setContinent(self, continent):
        self._continent
        return

    def getCity(self):
        return self._city

    def setCity(self, param):
        self._city = param
        return
