package components

import androidx.compose.desktop.ui.tooling.preview.Preview
import androidx.compose.material.AlertDialog
import androidx.compose.material.Button
import androidx.compose.material.ExperimentalMaterialApi
import androidx.compose.material.Text
import androidx.compose.runtime.*
import androidx.compose.ui.awt.ComposeWindow
import androidx.compose.ui.window.ApplicationScope
import androidx.compose.ui.window.Window
import controller.Character2DController
import data.FieldFromFileProvider
import model.Cell2D
import view.Field2DView
import java.awt.FileDialog
import java.io.File

@Suppress("OPT_IN_IS_NOT_ENABLED")
class App {
    @OptIn(ExperimentalMaterialApi::class)
    @Composable
    @Preview
    fun render(scope: ApplicationScope) {
        var cells by remember { mutableStateOf(mutableListOf<Cell2D>()) }
        var isWin by remember { mutableStateOf(false) }
        var update by remember { mutableStateOf(false) }

        val playerController = Character2DController(cells)
        val field2DView = Field2DView(cells, playerController)

        LaunchedEffect(update) {
            update = false
        }

        Window(onCloseRequest = scope::exitApplication,
            title = "Awesome resizable game",
            onKeyEvent = {
                val preWin = playerController.tryMove(it)
                if (!preWin) {
                    update = true
                } else {
                    isWin = true
                }
                false
            }) {
            if (isWin) {
                AlertDialog(onDismissRequest = {},
                    confirmButton = {
                        Button(onClick = {
                            scope.exitApplication()
                        }) {
                            Text("Win!")
                        }
                    },
                    text = { Text("Hello text") })
            } else {
                if (cells.isEmpty()) {
                    val files = openFileDialog(window, "Select field", listOf(".txt"), false)
                    if (files.isNotEmpty()) {
                        val fieldProvider = FieldFromFileProvider(files.first().name)
                        cells = fieldProvider.requireField().cells
                        playerController.updateFieldCells(cells)
                    }
                }
                field2DView.renderField(cells)
            }
        }
    }

    private fun openFileDialog(window: ComposeWindow, title: String, allowedExtensions: List<String>, allowMultiSelection: Boolean = true): Set<File> {
        return FileDialog(window, title, FileDialog.LOAD).apply {
            isMultipleMode = allowMultiSelection

            // windows
            file = allowedExtensions.joinToString(";") { "*$it" } // e.g. '*.jpg'

            // linux
            setFilenameFilter { _, name ->
                allowedExtensions.any {
                    name.endsWith(it)
                }
            }

            isVisible = true
        }.files.toSet()
    }
}
