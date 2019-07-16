/*
    GF3_11_高橋蓮
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BallGenerator : MonoBehaviour
{
 
    public GameObject[] ballPrefab;

    //ボールの種類
    enum Kind
    {
        None,
        Red,
        Blue,
        Green,
        Yellow,
        Black,
        Rainbow,
    };
	
    /*
     ボールの生成
    */
    public GameObject RandomGenerateBall()
    {
        //ボールの種類を決める
        int kind = Random.Range((int)Kind.None + 1, (int)Kind.Black + 1);

        GameObject obj = Instantiate(ballPrefab[kind], transform.position, transform.rotation) as GameObject;

        return obj;
    }

    public void GenerateRainbowBall()
    {
        //虹のボールを生成
        int kind = (int)Kind.Rainbow;

        GameObject obj = Instantiate(ballPrefab[kind], transform.position, transform.rotation) as GameObject;
    }
}
