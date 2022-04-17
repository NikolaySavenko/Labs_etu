package contacts.service

import contacts.*
import java.lang.System.Logger

class LoggedContactsService(private val contacts: ContactsService, private val logger: Logger): ContactsService {
    override fun addContact(person: Person, contact: Contact) {
        contacts.addContact(person, contact)
        logger.log(Logger.Level.INFO, "Contact $contact added to person $person")
    }

    override fun removeContact(person: Person, contact: Contact) {
        contacts.removeContact(person, contact)
        logger.log(Logger.Level.INFO, "Contact $contact removed from person $person")
    }

    override fun removePerson(person: Person) {
        contacts.removePerson(person)
        logger.log(Logger.Level.INFO, "Person $person removed")
    }

    override fun addPhone(person: Person, phone: Number, phoneType: PhoneType) {
        contacts.addPhone(person, phone, phoneType)
        logger.log(Logger.Level.INFO, "Phone $phone with type $phoneType added to person $person")
    }

    override fun addEmail(person: Person, email: String) {
        contacts.addEmail(person, email)
        logger.log(Logger.Level.INFO, "Email $email added to person $person")
    }

    override fun addLink(person: Person, link: Link) {
        contacts.addLink(person, link)
        logger.log(Logger.Level.INFO, "Link $link added to person $person")
    }

    override fun addAddress(person: Person, address: Address) {
        contacts.addAddress(person, address)
        logger.log(Logger.Level.INFO, "Address $address added to person $person")
    }

    override fun getPersonContacts(person: Person): List<Contact> {
        logger.log(Logger.Level.INFO, "Required contracts for person $person")
        return contacts.getPersonContacts(person)
    }

    override fun getPersonPhones(person: Person): List<Phone> {
        logger.log(Logger.Level.INFO, "Required phones for person $person")
        return contacts.getPersonPhones(person)
    }

    override fun getPersonEmails(person: Person): List<Email> {
        logger.log(Logger.Level.INFO, "Required emails for person $person")
        return contacts.getPersonEmails(person)
    }

    override fun getPersonLinks(person: Person): List<Link> {
        logger.log(Logger.Level.INFO, "Required links for person $person")
        return contacts.getPersonLinks(person)
    }

    override fun getAllPersons(): List<Person> {
        logger.log(Logger.Level.INFO, "Required all persons")
        return contacts.getAllPersons()
    }

    override fun getAllPersonsByFio(fioSubstring: String): List<Person> {
        logger.log(Logger.Level.INFO, "Required persons by fio $fioSubstring")
        return contacts.getAllPersonsByFio(fioSubstring)
    }

    override fun getAllContacts(): Map<Person, List<Contact>> {
        logger.log(Logger.Level.INFO, "Required ll contacts")
        return contacts.getAllContacts()
    }

    override fun removePersonContacts(person: Person) {
        logger.log(Logger.Level.INFO, "Removed contacts for person $person")
        return contacts.removePersonContacts(person)
    }

    override fun removePersonPhones(person: Person) {
        logger.log(Logger.Level.INFO, "Removed phones for person $person")
        return contacts.removePersonPhones(person)
    }

    override fun removePersonEmails(person: Person) {
        logger.log(Logger.Level.INFO, "Removed emails for person $person")
        return contacts.removePersonEmails(person)
    }

    override fun removePersonLinks(person: Person) {
        logger.log(Logger.Level.INFO, "Removed links for person $person")
        return contacts.removePersonLinks(person)
    }
}
