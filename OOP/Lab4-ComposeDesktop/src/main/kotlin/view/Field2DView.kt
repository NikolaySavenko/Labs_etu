package view

import androidx.compose.desktop.ui.tooling.preview.Preview
import androidx.compose.foundation.Canvas
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.material.MaterialTheme
import androidx.compose.runtime.Composable
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.geometry.Offset
import androidx.compose.ui.geometry.Size
import androidx.compose.ui.graphics.Color
import androidx.compose.ui.graphics.drawscope.drawIntoCanvas
import model.Cell2D


class Field2DView(private var cells: MutableList<Cell2D>) : View {
    @Composable
    @Preview
    override fun render() {
        renderField(cells)
    }

    @Composable
    fun renderField(cells: MutableList<Cell2D>) {
        MaterialTheme {
            Column(horizontalAlignment = Alignment.CenterHorizontally, modifier = Modifier.fillMaxWidth()) {
                Row {
                    Canvas(modifier = Modifier.fillMaxSize()) {
                        drawIntoCanvas {
                            val fieldWidth = cells.maxOf { it.x } + 1
                            val fieldHeight = cells.maxOf { it.y } + 1

                            val widthMultiplier = this.size.width / fieldWidth
                            val heightMultiplier = this.size.height / fieldHeight

                            cells.forEach {
                                val color = calculateCellColor(it.symbol)

                                drawRect(
                                    color = color,
                                    topLeft = Offset(
                                        widthMultiplier*it.x,
                                        heightMultiplier*it.y
                                    ),
                                    size = Size(
                                        this.size.width / fieldWidth,
                                        this.size.height / fieldHeight
                                    )
                                )
                            }
                        }
                    }
                }
            }
        }
    }

    private fun calculateCellColor(
        symbol: Char,
    ): Color {
        when (symbol) {
            '#' -> {
                return Color.DarkGray
            }
            'P' -> {
                return Color.Red
            }
            '-' -> {
                return Color.Gray
            }
            'E' -> {
                return Color.Green
            }
            else -> {
                return Color.Transparent
            }
        }
    }
}