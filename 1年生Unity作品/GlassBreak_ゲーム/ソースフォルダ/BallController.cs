/*
    GF3_11_高橋蓮
*/
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BallController : MonoBehaviour
{
    public int hp;
    public Sprite[] sprite;
    public GameObject explosion;
    private GameObject hitObject = null;
    GameManager gameManager;
    bool receiveDamageFlag = false;
    Vector2 vel;
    const int damageValue = 5;
    RainbowController controller = null;
    public AudioClip clash;
    public AudioClip hit;
    //hpの状態
    enum State
    {
        normal = 100,
        state1 = 60,
        state2 = 40,
        state3 = 20,
    };

	void Start ()
    {
        //ゲームマネージャの取得
        GameObject obj = GameObject.Find("gameManager");
        gameManager = obj.GetComponent<GameManager>();

        //コントローラの取得
        controller = this.GetComponent<RainbowController>();

        //ボールの初期設定
        hp = 100;
        //大きさをランダムに変える1倍から6倍まで
        float randSize = Random.Range(1.0f, 5.0f);
        this.transform.localScale *= randSize;
        //HPをランダムな値分減らす
        int randDamage = Random.Range(0, 40);
        hp -= randDamage;
        vel = new Vector2(0.0f, 30.0f);
    }

    void Update ()
    {
        Animation();
        //一定のスピードならダメージを受ける
        if(Mathf.Abs(GetComponent<Rigidbody2D>().velocity.y) >= Mathf.Abs(vel.y))
        {
            if(Mathf.Abs(GetComponent<Rigidbody2D>().velocity.x) >= Mathf.Abs(vel.x))
            {
                receiveDamageFlag = true;
            }
        }
        else
        {
            receiveDamageFlag = false;
        }
        //hpがなくなったらデストロイ！
        if (this.hp <= 0)
        {
            GetComponent<AudioSource>().PlayOneShot(clash);
            Instantiate(explosion, transform.position, transform.rotation);
            if (controller != null)
            {
                controller.DestroyEvent();
            }
            else
            {
                gameManager.AddDestroyBallCount();
            }

            Destroy(gameObject);
        }
	}

    void OnCollisionEnter2D(Collision2D obj)
    {
        //ゲームが始まっていないなら当たり判定をしない
        if (gameManager.GetState() != GameManager.StateId.wait)
        {
            if (receiveDamageFlag)
            {
                //ボールとの当たり判定を行う
                if (obj.gameObject.tag == "ball")
                {
                    //同じオブジェクトと連続で当たり判定しない
                    if (hitObject != obj.gameObject)
                    {
                        //お互いにダメージを受けさせる
                        ReceiveDamage();
                        obj.gameObject.GetComponent<BallController>().ReceiveDamage();
                        hitObject = obj.gameObject;
                        GetComponent<AudioSource>().PlayOneShot(hit);
                    }
                }
            }
        }
    }

    void ReceiveDamage()
    {
        this.hp -= damageValue;
    }

    void Animation()
    {
        if(hp <= (int)State.normal)
        {
            GetComponent<SpriteRenderer>().sprite = sprite[0];
        }
        if(hp <= (int)State.state1)
        {
            GetComponent<SpriteRenderer>().sprite = sprite[1];
        }
        if (hp <= (int)State.state2)
        {
            GetComponent<SpriteRenderer>().sprite = sprite[2];
        }
        if (hp <= (int)State.state3)
        {
            GetComponent<SpriteRenderer>().sprite = sprite[3];
        }
    }
}
