package controller

import androidx.compose.ui.ExperimentalComposeUiApi
import androidx.compose.ui.input.key.*
import model.Cell2D

class Character2DController(private var  cells: MutableList<Cell2D>) : CharacterController {
    @OptIn(ExperimentalComposeUiApi::class)
    override fun tryMove(event: KeyEvent): Boolean {
        if (event.type == KeyEventType.KeyDown) {
            val playerCell = cells.single { it.symbol == 'P' }
            val newPlayerCell : Cell2D
            val lastPlayerCell : Cell2D
            var relativeCell : Cell2D? = null

            when (event.key) {
                Key.W -> {
                    relativeCell = cells.singleOrNull { it.x == playerCell.x && it.y == playerCell.y - 1 }
                }
                Key.A -> {
                    relativeCell = cells.singleOrNull { it.x == playerCell.x - 1 && it.y == playerCell.y }
                }
                Key.S -> {
                    relativeCell = cells.singleOrNull { it.x == playerCell.x && it.y == playerCell.y + 1 }
                }
                Key.D -> {
                    relativeCell = cells.singleOrNull { it.x == playerCell.x + 1 && it.y == playerCell.y }
                }
            }

            if (relativeCell != null) {
                if (relativeCell.symbol == '-') {
                    newPlayerCell = Cell2D(relativeCell.x, relativeCell.y, playerCell.symbol)
                    lastPlayerCell = Cell2D(playerCell.x, playerCell.y, relativeCell.symbol)
                    cells.remove(playerCell)
                    cells.add(newPlayerCell)
                    cells.remove(relativeCell)
                    cells.add(lastPlayerCell)
                } else if (relativeCell.symbol == 'E') {
                    return true
                }
            }
        }
        return false
    }

    override fun updateFieldCells(newCells: MutableList<Cell2D>) {
        cells = newCells
    }
}