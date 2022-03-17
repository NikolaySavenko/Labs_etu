import address.AddressParser
import org.junit.jupiter.api.Test

import org.junit.jupiter.api.Assertions.*
import org.junit.jupiter.params.ParameterizedTest
import org.junit.jupiter.params.provider.ValueSource

internal class AddressKtTest {
    private val parser: AddressParser = AddressParser();

    @ParameterizedTest
    @ValueSource(
        strings = ["Индекс1, Название города 1, ул. Название улицы, д. Номер дома\n" +
                "Индекс2, Название города 2, ул. Название улицы, д. Номер дома\n" +
                "ИндексN, Название города N, ул. Название улицы, д. Номер дома\n"]
    )
    fun parseAddresses(source: String) {

    }

    @ParameterizedTest
    @ValueSource(
        strings = ["Индекс1, Название города 1, ул. Название улицы, д. Номер дома",
            "Индекс2, Название города 2, ул. Название улицы, д. Номер дома",
            "ИндексN, Название города N, ул. Название улицы, д. Номер дома"]
    )
    fun parseAddress(source: String) {
        val address = parser.parseAddress(source);
        assertNotNull(address)
        address!!

        assertNotNull(address.Index)
        assertNotNull(address.City)
        assertNotNull(address.HomeNumber)
    }
}