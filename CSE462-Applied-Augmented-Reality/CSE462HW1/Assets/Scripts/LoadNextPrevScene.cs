using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEditor;

public class LoadNextPrevScene : MonoBehaviour
{
    public string nextScene;
    public string prevScene;

    public void loadNext() {
        if(nextScene!=null) {
            SceneManager.LoadScene(nextScene);
        }
    }
    public void loadPrev() {
        if(prevScene!=null) {
            SceneManager.LoadScene(prevScene);
        }
    }
}
