// Copyright (c) 2019-2020 The Zcash developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php .
package logging

import (
	"context"
	"fmt"
	"os"
	"testing"

	"errors"
	"github.com/who-biz/lightwalletd/common"
	"github.com/sirupsen/logrus"
	"google.golang.org/grpc"
	"google.golang.org/grpc/peer"
)

var step int

func testhandler(ctx context.Context, req interface{}) (interface{}, error) {
	step++
	switch step {
	case 1:
		return nil, errors.New("test error")
	case 2:
		return nil, nil
	}
	return nil, nil
}

func TestLogInterceptor(t *testing.T) {
	output, err := os.OpenFile("test-log", os.O_CREATE|os.O_TRUNC|os.O_WRONLY, 0644)
	if err != nil {
		os.Stderr.WriteString(fmt.Sprint("Cannot open test-log:", err))
		os.Exit(1)
	}
	logger := logrus.New()
	logger.SetOutput(output)
	common.Log = logger.WithFields(logrus.Fields{
		"app": "test",
	})
	var req interface{}
	resp, err := LogInterceptor(peer.NewContext(context.Background(), &peer.Peer{}),
		&req, &grpc.UnaryServerInfo{}, testhandler)
	if err == nil {
		t.Fatal("unexpected success")
	}
	if resp != nil {
		t.Fatal("unexpected response", resp)
	}
	resp, err = LogInterceptor(context.Background(), &req, &grpc.UnaryServerInfo{}, testhandler)
	if err != nil {
		t.Fatal("unexpected error", err)
	}
	if resp != nil {
		t.Fatal("unexpected response", resp)
	}
	os.Remove("test-log")
	step = 0
}
