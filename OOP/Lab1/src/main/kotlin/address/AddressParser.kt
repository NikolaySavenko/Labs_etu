package address

class AddressParser {
    fun parseAddresses(addressesSource: String): MutableList<Address?> {
        val addresses = mutableListOf<Address?>()

        val pureAddress = addressesSource.split(System.lineSeparator())
        pureAddress.map {
            val address = parseAddress(it)
            addresses.add(address)
        }

        return addresses
    }

    fun parseAddress(address: String): Address? {
        return try {
            val parts = address.split(',')
            val index = parts[0].toInt()
            val city = parts[1].trimIndent()
            val street = parts[2].trimIndent()
            val houseNumber = parts[3].replace("д.", "").trimIndent().toInt()
            Address(index, city, street, houseNumber)
        } catch (exception: NumberFormatException) {
            null
        }
    }
}