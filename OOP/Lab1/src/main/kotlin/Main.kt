import address.AddressParser
import address.AddressUtils

fun main() {
    val source = buildString {
        append("123, Morioh, ул. Несокрушимого алмаза, д. 321")
        append(System.lineSeparator())
        append("584, Новая Москва, ул. Поросенка Петра, д. 52")
        append(System.lineSeparator())
        append("777, Санкт-Петербург, ул. Андрея Бреслава, д. -1")
    }

    val parser = AddressParser()
    val addresses = parser.parseAddresses(source)

    println("Source: $source")
    println("Parsed:")
    addresses.map {
        println(it)
    }

    val utils = AddressUtils()
    println("Min Index: ${utils.getWithMinIndex(addresses)}")
    println("Max Index: ${utils.getWithMaxIndex(addresses)}")
    println("Min Street: ${utils.getWithMinStreetLen(addresses)}")
    println("Max Street: ${utils.getWithMaxStreetLen(addresses)}")
}
