package shapes

import colors.Color
import kotlin.math.pow

data class Square(val width: Double, override val borderColor: Color, override val fillColor: Color) : ColoredShape2d {

    init {
        require(width > 0) { "width should be > 0" }
        require(borderColor.hex.isNotBlank()) { "borderColor should be not blank" }
        require(borderColor.hex.isNotBlank()) { "fillColor should be not blank" }
    }

    override fun calcArea(): Double {
        return width.pow(2)
    }
}