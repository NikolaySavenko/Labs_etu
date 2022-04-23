package shapes

import colors.Color

interface ColoredShape2d : Shape2d {
    val borderColor: Color
    val fillColor: Color
}