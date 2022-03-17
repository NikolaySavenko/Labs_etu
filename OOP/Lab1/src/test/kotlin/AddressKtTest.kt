import address.AddressParser
import org.junit.jupiter.api.Test

import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.params.ParameterizedTest
import org.junit.jupiter.params.provider.ValueSource

internal class AddressKtTest {
    private val parser: AddressParser = AddressParser()

    @Test
    fun parseAddresses() {
        val source = "123, Morioh, ул. Несокрушимого алмаза, д. 321" + System.lineSeparator() +
                "584, Новая Москва, ул. Поросенка Петра, д. 52" + System.lineSeparator() +
                "777, Санкт-Петербург, ул. Андрей Бреслава, д. -1"
        val addresses = parser.parseAddresses(source)
        addresses.map {
            assertNotNull(it)
            it!!

            assertNotNull(it.Index)
            assertNotNull(it.City)
            assertNotNull(it.Street)
            assertNotNull(it.HomeNumber)
        }
    }

    @ParameterizedTest
    @ValueSource(
        strings = ["123, Morioh, ул. Несокрушимого алмаза, д. 321",
            "584, Новая Москва, ул. Поросенка Петра, д. 52",
            "777, Санкт-Петербург, ул. Андрей Бреслава, д. -1"]
    )
    fun parseAddress(source: String) {
        val address = parser.parseAddress(source)
        assertNotNull(address)
        address!!

        assertNotNull(address.Index)
        assertNotNull(address.City)
        assertNotNull(address.Street)
        assertNotNull(address.HomeNumber)
    }
}