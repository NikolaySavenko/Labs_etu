package contacts.service

import contacts.*

class Contacts : ContactsService {
    private val persons: MutableMap<Person, MutableList<Contact>> = mutableMapOf()

    override fun addContact(person: Person, contact: Contact) {
        persons[person]!!.add(contact)
    }

    override fun removeContact(person: Person, contact: Contact) {
        persons[person]!!.remove(contact)
    }

    override fun removePerson(person: Person) {
        persons.remove(person)
    }

    override fun addPhone(person: Person, phone: Number, phoneType: PhoneType) {
        addContact(person, Phone(phone, phoneType))
    }

    override fun addEmail(person: Person, email: String) {
        addContact(person, Email(email))
    }

    override fun addLink(person: Person, link: Link) {
        addContact(person, link)
    }

    override fun addAddress(person: Person, address: Address) {
        addContact(person, address)
    }

    override fun getPersonContacts(person: Person): List<Contact> {
        return persons[person]!!.toList()
    }

    override fun getPersonPhones(person: Person): List<Phone> {
        return buildList {
            persons[person]!!.forEach {
                if (it is Phone) {
                    this.add(it)
                }
            }
        }
    }

    override fun getPersonEmails(person: Person): List<Email> {
        return buildList {
            persons[person]!!.forEach {
                if (it is Email) {
                    this.add(it)
                }
            }
        }
    }

    override fun getPersonLinks(person: Person): List<Link> {
        return buildList {
            persons[person]!!.forEach {
                if (it is Link) {
                    this.add(it)
                }
            }
        }
    }

    override fun getAllPersons(): List<Person> {
        return buildList {
            persons.keys.forEach {
                this.add(it)
            }
        }
    }

    override fun getAllPersonsByFio(fioSubstring: String): List<Person> {
        return buildList {
            persons.keys.forEach {
                if (fioSubstring in "${it.firstName} ${it.lastName}") {
                    this.add(it)
                }
            }
        }
    }

    override fun getAllContacts(): Map<Person, List<Contact>> {
        return buildMap {
            persons.forEach {
                this[it.key] = it.value
            }
        }
    }

    override fun removePersonContacts(person: Person) {
        this.persons.remove(person)
    }

    override fun removePersonPhones(person: Person) {
        persons[person]!!.forEach {
            if (it is Phone) {
                persons[person]!!.remove(it)
            }
        }
    }

    override fun removePersonEmails(person: Person) {
        persons[person]!!.forEach {
            if (it is Email) {
                persons[person]!!.remove(it)
            }
        }
    }

    override fun removePersonLinks(person: Person) {
        persons[person]!!.forEach {
            if (it is Link) {
                persons[person]!!.remove(it)
            }
        }
    }
}