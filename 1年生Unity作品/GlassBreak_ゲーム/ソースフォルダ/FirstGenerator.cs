/*
    GF3_11_高橋蓮
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FirstGenerator : MonoBehaviour
{
    public  int     generateNum = 0;            //生成するボールの数 
    public  int     generateTime = 0;           //生成する間隔　(秒)
    public  bool    generated = false;          //生成が終わったか
    public  int     changeTime = 0;             //シーンの状態を変えるまでの時間
    public  GameObject generateBackground;      //生成中の背景
    public  GameObject player;                  //プレイヤー
    public  GameObject startObj;                //スタート時のメッセージオブジェクト
    private int     generateCount = 0;          //生成したボールの数
    private int     timeCount = 0;              //時間のカウント
    BallGenerator   ballGenerator;              //ボールジェネレータースクリプト
    GameManager     gameManager;                //ゲームマネージャスクリプト
    GameObject      background;                 //生成した背景

	void Start ()
    {
        //ゲームマネージャの取得
        GameObject obj = GameObject.Find("gameManager");
        gameManager = obj.GetComponent<GameManager>();

        //ボールジェネレータの取得
        ballGenerator = this.GetComponent<BallGenerator>();

        //ジェネレート背景の生成
        background = Instantiate(generateBackground, generateBackground.transform.position, generateBackground.transform.rotation);
    }

    void Update ()
    {
        //一定時間すぎたら
        if(timeCount >= generateTime)
        {
            //指定された個数ボールを生成
            if (generateCount <= generateNum)
            {
                ballGenerator.RandomGenerateBall();
                generateCount++;
                //間隔のリセット
                timeCount = 0;
            }
            else
            {
                if(timeCount >= changeTime)
                {
                    Instantiate(startObj, startObj.transform.position, startObj.transform.rotation);
                    Destroy(background);
                    Instantiate(player, player.transform.position, player.transform.rotation);
                    Destroy(gameObject);
                }
            }
        }

        timeCount++;
    }
}
