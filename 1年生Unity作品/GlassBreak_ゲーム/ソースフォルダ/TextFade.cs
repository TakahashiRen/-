using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TextFade : MonoBehaviour
{
    Text text;
    float alpha = 0;

	void Start ()
    {
        text = this.GetComponent<Text>();
	}
	
	void Update ()
    {
        alpha+= 0.05f;
        text.color = new Color(text.color.r, text.color.g, text.color.b, Mathf.Sin(alpha));
	}
}
