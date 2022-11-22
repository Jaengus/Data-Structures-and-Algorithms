class TwoSum {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> v;
        v.push_back(0);
        v.push_back(nums.size() - 1);
            for (int a = v[0]; a < nums.size(); a++) {
        for (int b = v[1]; b >= 0; b--) {
            if (a == b)
                continue;
            else if (nums[a] + nums[b] == target) {
                v[0] = a;
                v[1] = b;
                return v;
            }
        }
    }
        return v;
    }
};
