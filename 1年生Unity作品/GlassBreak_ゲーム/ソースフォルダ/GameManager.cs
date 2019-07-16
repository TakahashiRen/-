/*
    GF3_11_高橋蓮
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    //プレイ中の状態
    public enum StateId
    {
        wait,
        play,
        clear,
        end,
    }
    StateId playState;
    Text scoreText;
    int destroyNum;
    int destroyCount;
    int destroyBallCount;
    int score;
    public ClearObject clearObj;
    bool clearFlag = false;

    void Start ()
    {
        scoreText = GameObject.Find("Text").GetComponentInChildren<Text>();
        playState = StateId.wait;
        destroyCount = 0;
        destroyBallCount = 0;
        score = 0;
	}
	
	void Update ()
    {
        //プレイ中にスコアの書き出しを行う
        if(playState == StateId.play)
        {
            //虹色のボールがすべて壊されたら
            //リザルトに移行
            if (destroyCount == destroyNum)
            {
                Instantiate(clearObj, clearObj.transform.position, clearObj.transform.rotation);
                ChangeState(StateId.clear);
            }
            scoreText.text = "SCORE:" + score.ToString();
        }
        if(playState == StateId.end)
        {
            PlayerPrefs.SetInt("PlayerScore", score);
            ChangeScene();
        }
        //escキーで終了
        if (Input.GetKeyDown(KeyCode.Escape))
        {
            Application.Quit();
        }

    }

    public void ChangeState(StateId nextState)
    {
        playState = nextState;
    }

    public StateId GetState()
    {
        return playState;
    }

    public void AddDestroyNum()
    {
        destroyNum++;
    }

    public void AddDestroyBallCount()
    {
        destroyBallCount++;
        AddScore();
    }

    public void AddDestroyRainbowCount()
    {
        destroyCount++;
        AddScore();
    }

    public void AddScore()
    {
        score += 500 * (destroyCount + 1);
    }

    void ChangeScene()
    {
        SceneManager.LoadScene("result");
    }

}
