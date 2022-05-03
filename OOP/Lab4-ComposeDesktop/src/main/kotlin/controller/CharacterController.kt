package controller

import androidx.compose.ui.input.key.KeyEvent
import model.Cell2D

interface CharacterController {
    fun tryMove(event: KeyEvent): Boolean
    fun updateFieldCells(newCells: MutableList<Cell2D>)
}