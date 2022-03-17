package address

class AddressUtils {
    fun getWithMaxIndex(addressess: MutableList<Address?>): Address? {
        var foundAddress: Address? = null

        addressess.map {
            if (foundAddress == null || (it != null && foundAddress!!.Index < it.Index)) {
                foundAddress = it
            }
        }
        return foundAddress
    }

    fun getWithMinIndex(addressess: MutableList<Address?>): Address? {
        var foundAddress: Address? = null

        addressess.map {
            if (foundAddress == null || (it != null && foundAddress!!.Index > it.Index)) {
                foundAddress = it
            }
        }
        return foundAddress
    }

    fun getWithMaxStreetLen(addressess: MutableList<Address?>): Address? {
        var foundAddress: Address? = null

        addressess.map {
            if (foundAddress == null || (it != null && foundAddress!!.Street.length < it.Street.length)) {
                foundAddress = it
            }
        }
        return foundAddress
    }

    fun getWithMinStreetLen(addresses: MutableList<Address?>): Address? {
        var foundAddress: Address? = null

        addresses.map {
            if (foundAddress == null || (it != null && foundAddress!!.Street.length > it.Street.length)) {
                foundAddress = it
            }
        }
        return foundAddress
    }
}