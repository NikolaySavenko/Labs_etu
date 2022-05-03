package data

import model.Cell2D
import model.Field
import model.Player2D

class EmptyFieldProvider : FieldProvider {
    private val sourceString = """
                        ########
                        ###----#
                        P-#-##-#
                        #---##-E
                        ########
                    """.trimIndent()

    private val field = parseFromString(sourceString)

    override fun requireField(): Field {
        return field
    }

    override fun getPlayer(): Player2D {
        return Player2D(1, 1)
    }

    private fun parseFromString(source: String): Field {
        val lines = sourceString.split('\n')
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
}