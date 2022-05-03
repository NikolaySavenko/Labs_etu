package data

import model.Cell2D
import model.Field
import model.Player2D
import java.io.File
import java.io.InputStream

class FieldFromFileProvider(fileName: String) : FieldProvider {
    val field = parseFromString(getStringFromFile(File(fileName)))

    override fun requireField(): Field {
        return field
    }

    override fun getPlayer(): Player2D {
        val cell = field.cells.find { it.symbol == 'P' }

        if (cell != null) {
            return Player2D(cell.x, cell.y)
        }

        return Player2D(0, 0)
    }

    private fun parseFromString(source: String): Field {
        val lines = source.split(System.lineSeparator())
        val cells = mutableListOf<Cell2D>()
        for(i in lines.indices) {
            for (j in 0 until lines[i].length) {
                val symbol = lines[i][j];
                if (symbol != ' ') {
                    cells.add(Cell2D(j, i, symbol))
                }
            }
        }
        return Field(cells)
    }

    private fun getStringFromFile(file: File): String {
        val inputStream: InputStream = file.inputStream()
        return inputStream.bufferedReader().use { it.readText() }
    }
}