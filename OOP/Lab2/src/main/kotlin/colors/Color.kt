package colors

data class Color(val hex: String) {
    init {
        require("#([0-9a-f]{3}|[0-9a-f]{6}|[0-9a-f]{8})".toRegex().matches(hex)) { "color should be hex" }
    }
}
