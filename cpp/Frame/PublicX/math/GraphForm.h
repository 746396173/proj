#pragma once
/*
@author zhp
@date 2017/3/14 4:40
@purpose for graph form
*/
//////////////////////////////////////////////////////////////////////////
template<typename DerivedT, typename VectorT>
class LineAlgoBase{
public:
	typedef VectorT VectorType;

protected:
	inline LineAlgoBase(const VectorType& pos1, const VectorType& pos2) : pos1_(pos1), pos2_(pos2){}

private:
	inline const DerivedT& GetDerived() const{
		return static_cast<const DerivedT&>(*this);
	}

public:
	inline const VectorType& GetPoint1() const{ return pos1_; }
	inline const VectorType& GetPoint2() const{ return pos2_; }
	//������֮��
	inline bool IsBetween(const VectorType& pos) const{
		if ((pos.x > pos1_.x && pos.x > pos2_.x) || (pos.x < pos1_.x && pos.x < pos2_.x))
			return false;
		if ((pos.y > pos1_.y && pos.y > pos2_.y) || (pos.y < pos1_.y && pos.y < pos2_.y))
			return false;
		return true;
	}
	//cursor��1��ʼ
	template<typename VecT>
	inline bool GetPosByStep(double step, int& cursor, VecT& out_pos) const{
		auto tmp = abs(pos1_.y - pos2_.y);
		auto tmp_out = out_pos.y;
		if (abs(pos1_.x - pos2_.x) > tmp)
		{
			if (pos1_.x > pos2_.x)
			{
				tmp = pos1_.x - step * cursor;
				if (tmp < pos2_.x)
					return false;
			}
			else
			{
				tmp = pos1_.x + step * cursor;
				if (tmp > pos2_.x)
					return false;
			}
			if (!GetDerived().GetY(tmp, tmp_out))
				return false;
			out_pos.x = tmp;
			out_pos.y = tmp_out;
		}
		else
		{
			if (pos1_.y > pos2_.y)
			{
				tmp = pos1_.y - step * cursor;
				if (tmp < pos2_.y)
					return false;
			}
			else
			{
				tmp = pos1_.y + step * cursor;
				if (tmp > pos2_.y)
					return false;
			}
			if (!GetDerived().GetX(tmp, tmp_out))
				return false;
			out_pos.x = tmp_out;
			out_pos.y = tmp;
		}
		++cursor;
		return true;
	}

protected:
	VectorType		pos1_;
	VectorType		pos2_;
};

//����ʽ����ʾ����(x0,y0)�ҷ�������Ϊ��u,v ����ֱ��
template<typename VectorT>
class LinePointForwardForm{
public:
	typedef VectorT VectorType;
	typedef typename VectorType::value_type value_type;

public:
	inline LinePointForwardForm(const VectorType& pos, const VectorType& vector);
};

//����ʽ����ʾ���㣨x0��y0������������a��b����ֱ��ֱ��
template<typename VectorT>
class LineNormalForm{
public:
	typedef VectorT VectorType;
	typedef typename VectorType::value_type value_type;

public:
	inline LineNormalForm(const VectorType& pos1, const VectorType& pos2);
};

//һ��ʽ
template<typename VectorT>
class LineGeneralForm : public LineAlgoBase<LineGeneralForm<VectorT>, VectorT>{
public:
	typedef VectorT VectorType;
	typedef typename VectorType::value_type value_type;

public:
	inline LineGeneralForm(const VectorType& pos1, const VectorType& pos2) : LineAlgoBase(pos1, pos2){
		if (pos1 == pos2)
		{
			assert(false);
			const_a_ = 0;
			const_b_ = 0;
			const_c_ = 0;
			return;
		}
		const_a_ = pos2.y - pos1.y;
		const_b_ = pos1.x - pos2.x;
		const_c_ = pos2.x * pos1.y - pos1.x * pos2.y;
	}
	inline bool GetX(value_type y, value_type& out_res) const{
		if (0 == const_a_)
		{
			if (y == pos1_.y)
			{
				out_res = pos1_.x;
				return true;
			}
			else if (y == pos2_.y)
			{
				out_res = pos2_.x;
				return true;
			}
			return false;
		}
		out_res = value_type((-const_c_ - const_b_ * y) / double(const_a_));
		return true;
	}
	inline bool GetY(value_type x, value_type& out_res) const{
		if (0 == const_b_)
		{
			if (x == pos1_.x)
			{
				out_res = pos1_.y;
				return true;
			}
			else if (x == pos2_.x)
			{
				out_res = pos2_.y;
				return true;
			}
			return false;
		}
		out_res = value_type((-const_c_ - const_a_ * x) / double(const_b_));
		return true;
	}
	//����
	inline bool GetFootPoint(const VectorType& pos, VectorType& foot_point) const{
		//����ʽ+һ��ʽ����
		//ֱ�ߵķ����������ǵ��봹��ķ�������
		auto pos_foot_vector = (pos1_ - pos2_).NormalVector();
		auto v_Au = const_a_ * pos_foot_vector.x;
		auto v_Bv = const_b_ * pos_foot_vector.y;
		auto denominator = v_Au + v_Bv;
		if (0 == denominator)
		{
			assert(!"pos1_==pos2_��ʱ��Ż�����������");
			return false;
		}
		foot_point.x = value_type((v_Bv * pos.x - const_b_ * pos_foot_vector.x * pos.y - pos_foot_vector.x * const_c_)
			/ double(denominator));
		foot_point.y = value_type((v_Au * pos.y - const_a_ * pos_foot_vector.y * pos.x - pos_foot_vector.y * const_c_) 
			/ double(denominator));
		return true;
	}
	//ֱ�߽���
	inline bool GetCrossPoint(const LineGeneralForm& rhs, VectorType& cross_point) const{
		auto denominator = rhs.const_a_ * const_b_ - rhs.const_b_ * const_a_;
		//�����ĸΪ0 ��ƽ�л���, ���ཻ
		if (0 == denominator) return false;
		cross_point.x = value_type((rhs.const_b_ * const_c_ - const_b_ * rhs.const_c_)
			/ double(denominator));
		cross_point.y = value_type((rhs.const_a_ * const_c_ - const_a_ * rhs.const_c_) 
			/ double(-denominator));
		return true;
	}
	//�㵽ֱ�ߵľ���
	inline double Distance(const VectorType& point) const{
		auto value = const_a_ * point.x + const_b_ * point.y + const_c_;
		if (value < 0) value = -value;
		return value / std::sqrt(double(const_a_ * const_a_ + const_b_ * const_b_));
	}

private:
	value_type		const_a_;
	value_type		const_b_;
	value_type		const_c_;
};
template<typename VectorT>
inline LineGeneralForm<VectorT> MakeLineGeneralForm(const VectorT& pos1, const VectorT& pos2){
	return LineGeneralForm<VectorT>(pos1, pos2);
}

//����ʽ��������Ҫ������������һ��ʽ
template<typename VectorT>
class LineTwoPointForm : public LineAlgoBase<LineTwoPointForm<VectorT>, VectorT>{
public:
	typedef VectorT VectorType;
	typedef typename VectorType::value_type value_type;

public:
	inline LineTwoPointForm(const VectorType& pos1, const VectorType& pos2) : LineAlgoBase(pos1, pos2){}
	inline bool GetX(value_type y, value_type& out_res) const{
		auto v = pos2_.y - pos1_.y;
		if (v == 0)
			return false;
		out_res = value_type((y - pos1_.y) / double(v) * (pos2_.x - pos1_.x) + pos1_.x);
		return true;
	}
	inline value_type GetY(value_type x, value_type& out_res) const{
		auto v = pos2_.x - pos1_.x;
		if (v == 0)
			return false;
		out_res = value_type((x - pos1_.x) / double(v) * (pos2_.y - pos1_.y) + pos1_.y);
		return true;
	}
};
template<typename VectorT>
inline LineTwoPointForm<VectorT> MakeLineTwoPointForm(const VectorT& pos1, const VectorT& pos2){
	return LineTwoPointForm<VectorT>(pos1, pos2);
}
//////////////////////////////////////////////////////////////////////////
//Բ�ı�׼����
template<typename VectorT, typename RadiusT>
class CircleStdForm{
public:
	typedef VectorT VectorType;
	typedef RadiusT RadiusType;

public:
	inline CircleStdForm(const VectorType& center, RadiusType radius) : center_(center), radius_(radius){
		assert(radius > 0);
		radius_square_ = radius * radius;
	}
	//����>0������Բ�⣻=0��Բ�ϣ�<0��Բ�ڡ�
	inline RadiusType GetPointPos(const VectorType& point) const{
		assert(radius_);
		double x_diff = point.x - center_.x, y_diff = point.y - center_.y;
		return (RadiusType)(x_diff * x_diff + y_diff * y_diff - radius_square_);
	}
	//����>0�����룻=0�����У�<0���ཻ
	inline RadiusType GetLinePos(const LineGeneralForm<VectorType>& line) const{
		return RadiusType(line.Distance(center_) - radius_);
	}
	//�߶���Բ�Ƿ���ڽ���
	inline bool SegmentIntersects(const LineGeneralForm<VectorType>& seg) const{
		if (GetLinePos(seg) > 0) return false;
		VectorType foot_point;
		if (!seg.GetFootPoint(center_, foot_point)) return false;		
		if (seg.IsBetween(foot_point)) return true;
		return GetPointPos(seg.GetPoint1()) <= 0 || GetPointPos(seg.GetPoint2()) <= 0;
	}

private:
	VectorType		center_;
	RadiusType		radius_;
	RadiusType		radius_square_;
};
template<typename VectorT, typename RadiusT>
inline CircleStdForm<VectorT, RadiusT> MakeCircleStdForm(const VectorT& center, RadiusT radius){
	return CircleStdForm<VectorT, RadiusT>(center, radius);
}
//////////////////////////////////////////////////////////////////////////