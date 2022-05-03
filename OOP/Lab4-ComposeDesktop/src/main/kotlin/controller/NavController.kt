package controller

import view.View

class NavController() {
    private var globalView: View? = null

    fun navigateTo(view: View) {
        globalView = view
    }
}
