using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TempScript : MonoBehaviour
{
    public GameObject test;

    
    // Start is called before the first frame update

    void Start()
    {
        test.SetActive(false);    
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    public void onclk() {
        test.SetActive(true);    

    }
}
