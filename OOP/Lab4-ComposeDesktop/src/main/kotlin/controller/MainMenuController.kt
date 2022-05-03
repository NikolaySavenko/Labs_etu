package controller

import data.FieldFromFileProvider
import data.FieldProvider
import view.Field2DView

class MainMenuController(private var targetViewNavigator: String) : IMainMenuController {
    override fun getFieldProvider() : FieldProvider {
        return FieldFromFileProvider("")
    }

    fun navigateToLabyrinth() {
        targetViewNavigator = Field2DView::class.java.name
    }
}