package shapes

import colors.Color
import kotlin.math.PI
import kotlin.math.pow

data class Circle(val radius: Double, override val borderColor: Color, override val fillColor: Color) : ColoredShape2d {
    init {
        require(radius > 0) { "Radius should be > 0" }
        require(borderColor.hex.isNotBlank()) { "borderColor should be not blank" }
        require(borderColor.hex.isNotBlank()) { "fillColor should be not blank" }
    }

    override fun calcArea(): Double {
        return PI * radius.pow(2)
    }
}