/*
* @Author: chenyizhuo.yizhuoc
* @Date:   2020-12-25 18:37:21
* @Last Modified by:   chenyizhuo.yizhuoc
* @Last Modified time: 2020-12-28 21:27:13
*/


/*
// This is the robot's control interface.
// You should not implement it, or speculate about its implementation
class Robot {
public:
	// Returns true if the cell in front is open and robot moves into the cell.
	// Returns false if the cell in front is blocked and robot stays in the current cell.
	bool move();

	// Robot will stay in the same cell after calling turnLeft/turnRight.
	// Each turn will be 90 degrees.
	void turnLeft();
	void turnRight();

	// Clean the current cell.
	void clean();
};
*/
 
struct PairHash {
	template <class T1, class T2>
	std::size_t operator()(std::pair<T1, T2> const &pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

enum Direction {
    UP = 0, LEFT, DOWN, RIGHT
};

Direction nextDirection(Direction dir) {
	return static_cast<Direction>((static_cast<int>(dir) + 1) % 4);
};

std::pair<int, int> coordinateForDirection(Direction dir, int x, int y) {
	if (dir == UP) {
		return std::make_pair(x, y - 1);
	} else if (dir == LEFT) {
		return std::make_pair(x - 1, y);
	} else if (dir == DOWN) {
		return std::make_pair(x, y + 1);
	} else if (dir == RIGHT) {
		return std::make_pair(x + 1, y);
	} else {
		return std::make_pair(x, y);
	}
}

void backtracking(Robot &robot, std::unordered_set<std::pair<int, int>, PairHash> &cleaned, int i, int j, Direction dir) {
    // std::cout << "check (" << i << ", " << j << "). dir = " << dir << std::endl;
	if (cleaned.count(std::make_pair(i, j))) {
		return;
	}

    // std::cout << "add (" << i << ", " << j << ") to set." << std::endl;
	cleaned.emplace(std::make_pair(i, j));
	robot.clean();

	for (int k = 0; k < 4; k++) {
		if (robot.move()) {
			std::pair p = coordinateForDirection(dir, i, j);
			backtracking(robot, cleaned, p.first, p.second, dir);
			robot.turnLeft();
			robot.turnLeft();
			robot.move();
			robot.turnLeft();
			robot.turnLeft();
		}
        dir = nextDirection(dir);
        robot.turnLeft();
	}
}

void cleanRoom(Robot &robot) {
    std::unordered_set<std::pair<int, int>, PairHash> cleaned;
    backtracking(robot, cleaned, 0, 0, UP);
}