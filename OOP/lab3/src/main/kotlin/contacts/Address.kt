package contacts

sealed class Address(val city: String, val street: String, val apartment: String): Contact()