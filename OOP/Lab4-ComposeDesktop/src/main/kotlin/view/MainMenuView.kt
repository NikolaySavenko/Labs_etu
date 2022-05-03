package view

import androidx.compose.desktop.ui.tooling.preview.Preview
import androidx.compose.material.Button
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Text
import androidx.compose.runtime.*
import components.FileDialogHelper
import controller.MainMenuController
import java.io.File
import java.io.InputStream

class MainMenuView(val controller: MainMenuController) : View {
    private val fileDialogHelper: FileDialogHelper = FileDialogHelper();

    @Composable
    @Preview
    override fun render() {
        var text by remember { mutableStateOf("Hello, World!") }
        var isFileChooserOpen by remember { mutableStateOf(false) }

        if (isFileChooserOpen) {
//            fileDialogHelper.openDialog(
//                onCloseRequest = { it ->
//                    val inputStream: InputStream = File(it!!).inputStream()
//                    val inputString = inputStream.bufferedReader().use { it.readText() }
//                    println(inputString)
//                }
//            )
        }

        MaterialTheme {
            Button(onClick = {
                text = "Hello, Desktop!"
//                isFileChooserOpen = true

            }) {
                Text(text)
            }
        }
    }
}