import contacts.service.Contacts
import contacts.service.LoggedContactsService

fun main() {
    println("Hello World!")

    val service = LoggedContactsService(Contacts(), System.getLogger("some logger"))
    println("$service has initialized")
}