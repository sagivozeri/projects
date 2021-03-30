class bank_account ():
    commission = 5.40
    def __init__(self, cliend_name, client_id, balance):
        self._client_name = cliend_name
        self._client_id = client_id
        self._balance = balance

    def withdraw(self, amount):
        if self._balance - amount > 0:
            self._balance -= (amount + bank_account.commission)
            return True
        return False

    def deposit(self, amount):
        self._balance += amount - bank_account.commission
        return True

    def __str__(self):
        return "client: {} has {}$".format(self._client_name, self._balance)

ba1 = bank_account("Sagiv", 12345678, 1000);
print(ba1)
ba1.deposit(500)
print(ba1)
ba1.withdraw(1400)
print(ba1)

