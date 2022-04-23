package colors

data class Color(val hex: String) {
    init {
        require(hex.matches("-?[0-9a-fA-F]+".toRegex())) { "color should be hex" }
    }
}
