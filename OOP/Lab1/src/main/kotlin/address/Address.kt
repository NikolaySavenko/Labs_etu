package address

data class Address(
    var Index: Int,
    var City: String,
    var HomeNumber: String
) {
    override fun equals(other: Any?): Boolean {
        if (this === other) return true
        if (javaClass != other?.javaClass) return false

        other as Address

        if (Index != other.Index) return false
        if (City != other.City) return false
        if (HomeNumber != other.HomeNumber) return false

        return true
    }

    override fun hashCode(): Int {
        var result = Index
        result = 31 * result + City.hashCode()
        result = 31 * result + HomeNumber.hashCode()
        return result
    }

    override fun toString(): String {
        return "Address(Index=$Index, City='$City', HomeNumber='$HomeNumber')"
    }
}
