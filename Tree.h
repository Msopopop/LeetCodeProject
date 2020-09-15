#pragma once
#include <memory>
#include <string>
namespace tree {
	enum class COLOR : bool
	{
		RED, BLACK
	};

	class basicNode {
	protected:
		basicNode() noexcept : index(0), value("")
		{
			;
		}
		basicNode(int index, const std::string& s):
			index(index), value(s) {
			;
		}
	public:
		virtual ~basicNode() = default;
	protected:
		virtual std::string& getValue() = 0;
		virtual int getIndex() const = 0;
		virtual size_t size() const = 0;
		virtual size_t height() const = 0;
		virtual bool contains(int index) const = 0;
		virtual std::string& get(int index) = 0;
		int index;
		std::string value;
	};

	class normalNode : public basicNode
	{
	public:	
		friend class BSTree;

		explicit normalNode(int index, const std:: string& s);
		~normalNode();
		inline std::string& getValue() override{ return value; }
		inline int getIndex() const override { return index; }
		
		std::unique_ptr<normalNode> leftNode;
		std::unique_ptr<normalNode> rightNode;

	private:
		size_t size() const override;
		size_t height() const override;
		bool contains(int index) const override;
		std::string& get(int index) override;
		void set(int index, const std::string& s);
	}; // class normalNode

	class LLRBNode : public basicNode {
	public:
		friend class LLRBTree;

		LLRBNode() = delete;
		LLRBNode(int index, const std::string& s, const COLOR& color);

		inline std::string& getValue() override { return value; }
		inline int getIndex() const override { return index; }

		std::unique_ptr<LLRBNode> leftNode;
		std::unique_ptr<LLRBNode> rightNode;
	private:
		void flipColor();
		size_t size() const override;
		size_t height() const override;
		bool contains(int index) const override;
		COLOR color;
		std::string& get(int index) override;
	}; //class LLRBNode

	class BNode : public basicNode {

	}; // class BNode

	class basicTree {
	protected:
		virtual ~basicTree() = default;
		virtual size_t size() const = 0;
		virtual size_t height() const = 0;
		virtual bool contains(int index) const = 0;
		virtual std::string& get(int index) = 0;
		virtual void set(int index, const std::string& s) = 0;
	};

	class BSTree : public basicTree
	{
	public:
		BSTree() = delete;
		explicit BSTree(int index ,const std::string& s);

		inline size_t size() const override { return root->size(); }
		inline size_t height() const override { return root->height(); }
		inline bool contains(int index) const override { return root->contains(index); }
		std::string& get(int index) override;
		void set(int index, const std::string& s) override { root->set(index, s); }
	private:
		std::unique_ptr<normalNode> root;
	}; // class BSTree

	class LLRBTree : public basicTree{
	public:
		LLRBTree() = delete;
		explicit LLRBTree(int index, const std::string& s);
		inline size_t size() const override { return root->size(); }
		inline size_t height() const override  { return root->height(); }
		inline bool contains(int index) const override { return root->contains(index); }
		std::string& get(int index) override;
		inline void set(int index, const std::string& s) override
		{ 
			root = set(root, index, s); 
			// root must be BLACK ALWAYS
			if (!root)
			root->color = COLOR::BLACK; 
		}
	private:
		std::unique_ptr<LLRBNode>&& set
		(std::unique_ptr<LLRBNode>& node, int index, const std::string& s);

		static bool isRed(const std::unique_ptr<LLRBNode>& node);
		static void rotateLeft(std::unique_ptr<LLRBNode>& node);
		static void rotateRight(std::unique_ptr<LLRBNode>& node);
		std::unique_ptr<LLRBNode> root;
	}; // class LLRBTree

	class BTree :public basicTree {

	}; // class BTree

} // namespace tree
