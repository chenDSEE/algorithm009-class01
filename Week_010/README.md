# 动态规划感悟

- 最优子结构
- 当前问题的最优解 = curr_direction_influence + sub_problem_prefect_solution
  				= for ( each direction ) + sub_problem_prefect_solution
  				= best_of( for (each_direction_influence + sub_problem_prefect_solution_for_curr_direction) )

problem(curr_level) = influence(curr_level_each_choose) + sub_problem_prefect_solution(curr_level_each_choose)
                    = best_of(each_choose_influencr + each_choose_corresponding_dp_status)

- 选择最佳当前可能性（不同选择的影响 + 不同选择对应的子状态的最优情况）

- 重点：选出当前所有决策中的最优方案（influence(当前可能的决策方案) + 当前决策所需子问题的最优解状态是哪个）
  	==> 当前能做出那几个选择 + 每个选择所对应的子问题的最优解
  	==> 得出当前状态下，能做出的所有选择下得到的结果，然后选出当中的最优解，然后放进 dp_status 中，
  	    成为接下来的大问题所需要的 子问题最优解

- 今天结束之后，可以有什么状态？ 
  - --> 要达成今天结束时的状态 A 的话，当下可以有什么行动？分别由那里平行宇宙发展而来？ --> 选取最佳的那个作为状态 A 下的今天战果
  - --> 要达成今天结束时的状态 B 的话，当下可以有什么行动？分别由那里平行宇宙发展而来？ --> 选取最佳的那个作为状态 B 下的今天战果
- dp_status 根据拥有/记载了全部历史影响的 dp_status 来生成新的 dp_status
  - 有选择的继承旧的 dp_status
  - DP -> 能够到达当前这个 dp_status 优很多种方法，的但是我只继承我当下能够继承的最好上一步 + 本次行动会产生的结果，更行本次的状态
  - 不关心怎么到上一步，只关心到上一步的话，最优情况是什么
  - 已知当前 step 要到达哪几种状态，而这个状态就是从旧状态（从几个不同的平行宇宙走过来）变过来的





ps: 其余总结见具体代码文件，及思维导图