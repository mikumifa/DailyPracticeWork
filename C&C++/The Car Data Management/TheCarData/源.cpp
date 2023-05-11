#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;
//绩效类
class Performance {
public:
	virtual double calculatePerformance(double income) {
		return 0.3;  // 当前绩效系数为0.3
	}
};

// 本公司绩效类类
class CompanyDriverPerformance :public Performance {
public:
	double calculatePerformance(double income) override {
		return (income > 0) ? (income / 300000) : 0;
	}

};

// 挂靠绩效类类
class AffiliatedDriverPerformance :public Performance {
public:

	double calculatePerformance(double income) override {
		// 返回绩效系数（0~1之间）
		return (income > 0) ? (income / 600000) : 0;
	}

};
// 司机类
class Driver {
public:
	string name;      // 姓名
	string plateNo;  // 编号
	string type = "in";      // 司机类型
	Performance* performance; //绩效

};

// 车辆类
class Vehicle {
public:
	string plateNo;     // 车牌
	string color;       // 颜色
	double maxLoad;     // 最大载重
};

// 作业记录类
class JobRecord {
public:
	string jobDate;       // 作业日期
	string containerNo;   // 集装箱号
	string containerSize; // 箱型尺寸
	double freight;       // 运价
	double cost;          // 成本
	Driver driver; //司机
	void show() const {
		cout << jobDate << "\t" << containerNo << "\t" << containerSize << "\t"
			<< freight << "\t" << cost << "\t" << driver.plateNo << "\t" << driver.name << endl;
	}
};

// 绩效类


// 数据处理类
class DataProcessor {
public:
	vector<JobRecord> records;
	map<string, vector<JobRecord>> jobRecordDriverList;
	map<string, vector<JobRecord>> jobRecordCarList;
	void read_data(const string& filename) {
		ifstream fin(filename);
		if (!fin) {
			cerr << "Failed to open file " << filename << endl;
			exit(1);
		}
		string line;
		while (getline(fin, line)) {
			stringstream ss(line);
			string date, container_no, container_type, fare_str, cost_str, license, driver;
			ss >> date >> container_no >> container_type >> fare_str >> cost_str >> license >> driver;
			// 处理车牌号中的地区代码
			if (license.size() == 6)
				license.erase(0, 1);
			if (license.size() != 5)
				continue;
			//cout << license << endl;
			if (license.size() != 0 && !isdigit(license[0]) && !isalpha((license[0])))
				continue;
			// 去除运价和成本中的引号
			fare_str.erase(remove(fare_str.begin(), fare_str.end(), '\"'), fare_str.end());
			cost_str.erase(remove(cost_str.begin(), cost_str.end(), '\"'), cost_str.end());
			fare_str.erase(remove(fare_str.begin(), fare_str.end(), ','), fare_str.end());
			cost_str.erase(remove(cost_str.begin(), cost_str.end(), ','), cost_str.end());
			// 将运价和成本字符串转换为double类型
			double fare, cost;
			try {
				fare = stod(fare_str);
				cost = stod(cost_str);
			}
			catch (const std::invalid_argument& error) {
				continue;
			}
			// 如果运价和成本都为0，但是是拼箱，则记录为有效数据
			if (fare == 0 && cost == 0 && container_type == "CFS") {
				JobRecord r = { date, container_no, container_type, fare, cost, {driver, license,"in",new CompanyDriverPerformance()} };
				records.push_back(r);
			}
			// 如果运价和成本不为0，或者是大件或散货，则记录为有效数据
			else if ((fare != 0 || cost != 0) && container_type != "CFS") {
				JobRecord r = { date, container_no, container_type, fare, cost, {driver, license,"in",new CompanyDriverPerformance()} };
				records.push_back(r);
			}
			else {
				continue;
			}
			/*     string jobDate;       // 作业日期
				string containerNo;   // 集装箱号
				string containerSize; // 箱型尺寸
				double freight;       // 运价
				double cost;          // 成本
				string plateNo;       // 车牌
				string driverName;    // 司机姓名 */
				// 如果出现除车牌或司机外，其他数据项完整，则该作业属于紧邻的前一个司机及相应车辆
			if (records.size() > 0 && records.back().driver.name.empty() && records.back().driver.plateNo.empty()) {
				records.back().driver.plateNo = records[records.size() - 2].driver.plateNo;
				records.back().driver.name = records[records.size() - 2].driver.name;
			}
			jobRecordDriverList[records.back().driver.name].push_back(records.back());
			jobRecordCarList[records.back().driver.plateNo].push_back(records.back());
			//records.back().show();
		}
		fin.close();
	}

	void print_records() const {
		for (const auto& r : records) {
			r.show();
		}
	}
};
int getMonth(JobRecord job) {
	string month = job.jobDate.substr(5, job.jobDate.find("/", 5) - 5);
	int index = job.jobDate.find("/", 5);

	return stoi(month);

}
double calculateAllDriverRevenue(int month, DataProcessor& dataProcessor) {
	double ans = 0;
	for (auto& jobRecordDriver : dataProcessor.jobRecordDriverList) {
		// 计算总运价和总成本
		double totalRevenue = 0.0;
		double totalCost = 0.0;
		for (auto& jobRecord : jobRecordDriver.second) {
			if (getMonth(jobRecord) == month) {
				totalRevenue += jobRecord.freight;
				totalCost += jobRecord.cost;
			}

		}
		// 计算绩效系数和司机收入
		double income = totalRevenue - totalCost;
		double performanceCoefficient = jobRecordDriver.second[0].driver.performance->
			calculatePerformance(income);
		double driverRevenue = performanceCoefficient * income;
		ans += driverRevenue;
	}
	return ans;
}
void calculateDriverRevenue(int month, DataProcessor& dataProcessor) {
	cout << month << "月" << "如下" << endl;
	for (auto& jobRecordDriver : dataProcessor.jobRecordDriverList) {
		// 计算总运价和总成本
		double totalRevenue = 0.0;
		double totalCost = 0.0;
		for (auto& jobRecord : jobRecordDriver.second) {
			if (getMonth(jobRecord) == month) {
				totalRevenue += jobRecord.freight;
				totalCost += jobRecord.cost;
			}

		}
		// 计算绩效系数和司机收入
		double income = totalRevenue - totalCost;
		double performanceCoefficient = jobRecordDriver.second[0].driver.performance->calculatePerformance(income);
		double driverRevenue = performanceCoefficient * income;
		// 输出结果
		if (jobRecordDriver.first == "")
			continue;
		cout << "司机 " << jobRecordDriver.first << " 的作业情况如下：" << endl;
		cout << month << "月总运价：" << totalRevenue << " 元" << endl;
		cout << month << "月总成本：" << totalCost << " 元" << endl;
		cout << "司机收入（绩效系数为 " << performanceCoefficient << "）：" << driverRevenue << " 元" << endl;
		cout << endl;
	}

}
void calculateVehicleTransportVolume(int month, DataProcessor& dataProcessor) {
	// 计算运输量
	cout << month << "月" << "如下" << endl;
	for (auto& vehicle : dataProcessor.jobRecordCarList) {
		int transportVolume = 0;
		for (auto& jobRecord : vehicle.second) {
			if (getMonth(jobRecord) == month) {
				string transportVolumeStr = jobRecord.containerSize;
				if (transportVolumeStr == "CFS")
					continue;
				transportVolumeStr.erase(transportVolumeStr.end() - 2, transportVolumeStr.end());

				try {
					transportVolume += stoi(transportVolumeStr);
				}
				catch (const std::invalid_argument) {
				}
			}
		}
		// 输出结果
		cout << "车牌为 " << vehicle.first << " 的车辆在" << month << "月的运输量为：" << transportVolume << " TEU" << endl;
		cout << endl;
	}

}
double calculateAllVehicleTransportVolume(int month, DataProcessor& dataProcessor) {
	// 计算运输量
	double ans = 0;
	for (auto& vehicle : dataProcessor.jobRecordCarList) {
		int transportVolume = 0;
		for (auto& jobRecord : vehicle.second) {
			if (getMonth(jobRecord) == month) {
				string transportVolumeStr = jobRecord.containerSize;
				if (transportVolumeStr == "CFS")
					continue;
				transportVolumeStr.erase(transportVolumeStr.end() - 2, transportVolumeStr.end());

				try {
					transportVolume += stoi(transportVolumeStr);
				}
				catch (const std::invalid_argument) {
				}
			}
		}
		// 输出结果
		ans += transportVolume;
	}
	return ans;
}
void calculateCompanyTransportVolume(int month, DataProcessor& dataProcessor) {
	// 计算总运价和总成本
	cout << month << "月" << "如下" << endl;
	double totalRevenue = 0.0;
	double totalCost = 0.0;
	for (auto& jobRecord : dataProcessor.records) {
		if (getMonth(jobRecord) == month) {
			totalRevenue += jobRecord.freight;
			totalCost += jobRecord.cost;
		}
	}
	cout << "公司" << month << "月的运输量，总成本，净利润（总运价 - 总成本 - 司机收入）为" << calculateAllVehicleTransportVolume(month, dataProcessor) <<
		"," << totalCost << "," << totalRevenue - totalCost - calculateAllDriverRevenue(month, dataProcessor) << endl;
	cout << endl;
}
int main() {
	DataProcessor dataProcessor;
	dataProcessor.read_data("data.txt");
	int choice;

	do {
		cout << "请选择要执行的操作：" << endl;
		cout << "1. 计算每月司机的运输量和收入" << endl;
		cout << "2. 计算每月车辆创造的运输量" << endl;
		cout << "3. 计算公司每月的运输量、总成本和净利润" << endl;
		cout << "4. 查询司机作业清单" << endl;
		cout << "5. 查询车辆作业清单" << endl;
		cout << "6. 退出" << endl;
		cin >> choice;
		int month; string input;
		switch (choice) {
		case 1:
			for (int i = 1; i <= 12; i++) {
				calculateDriverRevenue(i, dataProcessor); // 计算每月司机的运输量和收入
			}
			break;
		case 2:
			for (int i = 1; i <= 12; i++)
				calculateVehicleTransportVolume(i, dataProcessor); // 计算每月车辆创造的运输量
			break;
		case 3:
			for (int i = 1; i <= 12; i++)
				calculateCompanyTransportVolume(i, dataProcessor); // 计算公司每月的运输量、总成本和净利润
			break;
		case 4:
			cout << "输入月份和司机姓名（用空格隔开）: ";
			cin >> month >> input;
			cout << "作业日期  集装箱号   箱型尺寸  运价   成本   车牌（默认辽B） 司机" << endl;
			for (auto& i : dataProcessor.jobRecordDriverList[input]) {
				if (getMonth(i) == month)
					i.show();
			}

			break;
		case 5:
			cout << "输入月份和车牌（用空格隔开）: ";
			cin >> month >> input;
			cout << "作业日期  集装箱号   箱型尺寸  运价   成本   车牌（默认辽B） 司机" << endl;
			for (auto& i : dataProcessor.jobRecordCarList[input]) {
				if (getMonth(i) == month)
					i.show();
			}

			break;
		case 6:
			cout << "谢谢使用！" << endl;
			break;
		default:
			cout << "无效的选项，请重新输入！" << endl;
			break;
		}
	} while (choice != 6);

	return 0;
}