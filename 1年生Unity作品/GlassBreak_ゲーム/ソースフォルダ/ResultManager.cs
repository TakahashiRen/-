using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class ResultManager : MonoBehaviour
{
    Text text;
    int score;
	void Start ()
    {
        GameObject obj = GameObject.Find("ScoreText");
        text = obj.GetComponent<Text>();
        score = PlayerPrefs.GetInt("PlayerScore");
        text.text = "SCORE\n" + score.ToString();
	}
	
	void Update ()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            ChangeScene();
        }
        //escキーで終了
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }

    }

    void ChangeScene()
    {
        SceneManager.LoadScene("title");
    }
}
