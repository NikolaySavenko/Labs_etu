package data

import model.Field
import model.Player2D

interface FieldProvider {
    fun requireField() : Field
    fun getPlayer(): Player2D
}