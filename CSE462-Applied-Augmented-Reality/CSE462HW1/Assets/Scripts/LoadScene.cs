

using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEditor;

public class LoadScene : MonoBehaviour {

    private void Start() {
    }
    private void Update() {
        
    }
        
    public void loadFirst() {
        SceneManager.LoadScene("FirstGroupScene");
    }
    public void loadSecond() {
        SceneManager.LoadScene("SecondGroupScene");
        
    }
    public void loadThird() {
        SceneManager.LoadScene("ThirdGroupScene");

    }
    public void loadFourth() {
        SceneManager.LoadScene("FourthGroupScene");
    }
    public void loadFifth() {
        SceneManager.LoadScene("FifthGroupScene");
    }
    public void loadSixth() {
        SceneManager.LoadScene("SixthGroupScene");
    }    
}
