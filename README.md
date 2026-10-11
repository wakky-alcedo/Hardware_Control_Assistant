# Hardware Control Assistant - 1.0.0

## util

## filter

## output
- `suppress_abs()`: 絶対値の上限で頭打ちにする
- `limit_rate()`: 今の値から目標値へ，変化の速さの上限を守って dt 秒で動ける分だけ近づける．
  加速 (0 から離れる向き)・減速 (0 に近づく向き) それぞれに上限 [unit/s] を付けられる (0 以下で制限なし)
  ```c++
  // 0→1 を最短 0.5 s，1→0 を最短 0.25 s で変える
  const hca::RateLimit<float> limit{2.0f, 4.0f};
  duty = hca::limit_rate(duty, target_duty, limit, dt);  // dt: 前回からの経過時間 [s]
  ```
- `RateLimiter`: `limit_rate()` に今の値を覚えさせたクラス
  ```c++
  hca::RateLimiter<float> limiter(limit);
  float duty = limiter.update(target_duty, dt);
  limiter.reset();  // 非常停止などで制限を無視して 0 にする
  ```
